/*------------------------------------------------------------------------*/
/* Sample Code of OS Dependent Functions for FatFs (libultra)             */
/* (C)ChaN, 2018    (C)devwizard, 2022                                    */
/*------------------------------------------------------------------------*/


#include "ff.h"


#if FF_USE_LFN == 3	/* Dynamic memory allocation */

/*------------------------------------------------------------------------*/
/* Allocate a memory block                                                */
/*------------------------------------------------------------------------*/

void* ff_memalloc (	/* Returns pointer to the allocated memory block (null if not enough core) */
	UINT msize		/* Number of bytes to allocate */
)
{
	return malloc(msize);	/* Allocate a new memory block with POSIX API */
}


/*------------------------------------------------------------------------*/
/* Free a memory block                                                    */
/*------------------------------------------------------------------------*/

void ff_memfree (
	void* mblock	/* Pointer to the memory block to free (nothing to do if null) */
)
{
	free(mblock);	/* Free the memory block with POSIX API */
}

#endif



#if FF_FS_REENTRANT	/* Mutal exclusion */

/*------------------------------------------------------------------------*/
/* Create a Synchronization Object                                        */
/*------------------------------------------------------------------------*/
/* This function is called in f_mount() function to create a new
/  synchronization object for the volume, such as semaphore and mutex.
/  When a 0 is returned, the f_mount() function fails with FR_INT_ERR.
*/

static OSAccessQueue AccessQueue[FF_VOLUMES];	/* Table of OSAccessQueue */


int ff_cre_syncobj (	/* 1:Function succeeded, 0:Could not create the sync object */
	BYTE vol,			/* Corresponding volume (logical drive number) */
	FF_SYNC_t* sobj		/* Pointer to return the created sync object */
)
{
	OSAccessQueue *acs = *sobj = &AccessQueue[vol];
	osCreateMesgQueue(&acs->mq, acs->msg, 1);
	osSendMesg(&acs->mq, (OSMesg)1, OS_MESG_NOBLOCK);
	return 1;
}


/*------------------------------------------------------------------------*/
/* Delete a Synchronization Object                                        */
/*------------------------------------------------------------------------*/
/* This function is called in f_mount() function to delete a synchronization
/  object that created with ff_cre_syncobj() function. When a 0 is returned,
/  the f_mount() function fails with FR_INT_ERR.
*/

int ff_del_syncobj (	/* 1:Function succeeded, 0:Could not delete due to an error */
	FF_SYNC_t sobj		/* Sync object tied to the logical drive to be deleted */
)
{
	(void)sobj;
	return 1;
}


/*------------------------------------------------------------------------*/
/* Request Grant to Access the Volume                                     */
/*------------------------------------------------------------------------*/
/* This function is called on entering file functions to lock the volume.
/  When a 0 is returned, the file function fails with FR_TIMEOUT.
*/

int ff_req_grant (	/* 1:Got a grant to access the volume, 0:Could not get a grant */
	FF_SYNC_t sobj	/* Sync object to wait */
)
{
#if FF_FS_TIMEOUT < 0
	if (osRecvMesg(&sobj->mq, NULL, OS_MESG_NOBLOCK) < 0) return 0;
	return 1;
#endif
#if FF_FS_TIMEOUT == 0
	osRecvMesg(&sobj->mq, NULL, OS_MESG_BLOCK);
	return 1;
#endif
#if FF_FS_TIMEOUT > 0
	OSMesg msg;
	OSTimer timer;
	osSetTimer(&timer, FF_FS_TIMEOUT, 0, &sobj->mq, (OSMesg)0);
	osRecvMesg(&sobj->mq, &msg, OS_MESG_BLOCK);
	osStopTimer(&timer);
	if (msg) osRecvMesg(&sobj->mq, NULL, OS_MESG_NOBLOCK);
	return (int)msg;
#endif
}


/*------------------------------------------------------------------------*/
/* Release Grant to Access the Volume                                     */
/*------------------------------------------------------------------------*/
/* This function is called on leaving file functions to unlock the volume.
*/

void ff_rel_grant (
	FF_SYNC_t sobj	/* Sync object to be signaled */
)
{
	osSendMesg(&sobj->mq, (OSMesg)1, OS_MESG_BLOCK);
}

#endif

