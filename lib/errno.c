#include <errno.h>
#include <unistd.h>

int errno;

const char *strerror(int error) {
    switch (error) {
    case ERROR:		return "ERROR";
    case EPERM:		return "EPERM";
    case ENOENT:	return "ENOENT";
    case ESRCH:		return "ESRCH";
    case EINTR:		return "EINTR";
    case EIO:		return "EIO";
    case ENXIO:		return "ENXIO";
    case E2BIG:		return "E2BIG";
    case ENOEXEC:	return "ENOEXEC";
    case EBADF:		return "EBADF";
    case ECHILD:	return "ECHILD";
    case EAGAIN:	return "EAGAIN";
    case ENOMEM:	return "ENOMEM";
    case EACCES:	return "EACCES";
    case EFAULT:	return "EFAULT";
    case ENOTBLK:	return "ENOBLK";
    case EBUSY:		return "EBUSY";
    case EEXIST:	return "EEXIST";
    case EXDEV:		return "EXDEV";
    case ENODEV:	return "ENODEV";
    case ENOTDIR:	return "ENOTDIR";
    case EISDIR:	return "EISDIR";
    case EINVAL:	return "EINVAR";
    case ENFILE:	return "ENFILE";
    case EMFILE:	return "EMFILE";
    case ENOTTY:	return "ENOTTY";
    case ETXTBSY:	return "ETXTBSY";
    case EFBIG:		return "EFBIG";
    case ENOSPC:	return "ENOSPC";
    case ESPIPE:	return "ESPIPE";
    case EROFS:		return "EROFS";
    case EMLINK:	return "EMLINK";
    case EPIPE:		return "EPIPE";
    case EDOM:		return "EDOM";
    case ERANGE:	return "ERANGE";
    case EDEADLK:	return "EDEADLK";
    case ENAMETOOLONG:	return "ENAMETOOLONG";
    case ENOLCK:	return "ENOLCK";
    case ENOSYS:	return "ENOSYS";
    case ENOTEMPTY:	return "ENOTEMPTY";

    }
}
