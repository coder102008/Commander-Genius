/*
 * CPlatform.h
 *
 *  Created on: 23.02.2011
 *      Author: gerstrong
 *
 *  This handles the floating platforms in Galaxy
 */

#ifndef CPLATFORM_H_
#define CPLATFORM_H_

#include "common/CObject.h"

namespace galaxy {

#define A_PLATFORM_MOVE	0	/* Ordinary moving platform */
#define A_PLATFORM_SIT	1	/* Dropping platform waiting for passenger */
#define A_PLATFORM_DROP	2	/* Dropping platform dropping */
#define A_PLATFORM_RISE	3	/* Dropping platform dropping */

class CPlatform : public CObject {
public:
	CPlatform(CMap *pmap, Uint32 x, Uint32 y, direction_t dir);
	void process();
};

}

#endif /* CPLATFORM_H_ */
