// di.h
// an implementation of high-level disk drive access

#ifdef _DI_H
#define _DI_H

// How to use:
// di_init() must be called before anything else in order to set up the disk
// drive. di_init() can be called with 0 as an argument to disable DI
// temporarily.
// If necessary use di_setbuf() to set a custom read/write buffer for disk
// access; normally this is not needed, but it can be useful to simplify
// sequential disk accesses.
// From there, use di_read() and di_write() to read and write sectors,
// respectively.

// di_init(): Sets up the drive interface
//  offset: address in memory of the drive window
//  if offset is 0, the iface becomes "deinitialized."
// returns: 0 on success, 1 on failure
// NOTE: Currently doesn't ever fail detectably
int di_init ( void *offset );

// di_read(): Read a sector from the disk
//  sec: sector number to read
// returns: 1 on drive not ready, 2 on read failure, else 0
int di_read ( int sec );

// di_write(): Write a sector to the disk
//  sec: sector number to read
// returns: 1 on drive not ready, 2 on write failure, else 0
int di_write ( int sec );

// di_setbuf(): Set the memory buffer for reading/writing
//  buf: pointer to memory for buffering. If 0, no buffer copying will be done.
// NOTE: The buffer needs to be at least 0x80 (128) bytes in size.
void di_setbuf ( void *buf );

// di_getbuf(): Returns the current pointer to the disk buffer
void *di_getbuf ( void );

#endif // _DI_H
