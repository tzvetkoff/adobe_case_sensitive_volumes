#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include "dyld-interposing.h"
#include <CoreServices/CoreServices.h>

static OSStatus _FSGetVolumeParms(FSVolumeRefNum volume, GetVolParmsInfoBuffer *buffer, ByteCount bufferSize) {
	OSStatus status = FSGetVolumeParms(volume,buffer,bufferSize);
	int isCaseSensitive = !!(buffer->vMExtendedAttributes & (1 << bIsCaseSensitive));

	if(isCaseSensitive) {
		printf("== FSGetVolumeParms - lying and saying the volume is case insensitive, though it is case sensitive. ==\n");
		buffer->vMExtendedAttributes &= ~(1 << bIsCaseSensitive);
	}

	return status;
}

DYLD_INTERPOSE(_FSGetVolumeParms, FSGetVolumeParms);
