/*
 * CPassive.h
 *
 *  Created on: 31.01.2010
 *      Author: gerstrong
 */

#ifndef CPASSIVE_GALAXY_H_
#define CPASSIVE_GALAXY_H_

#include "../CPassive.h"
#include <string>

namespace galaxy
{

class CPassiveGalaxy : public CPassive
{
public:
	CPassiveGalaxy();

	bool init(char mode);
    void ponder();
    void render();
	void processIntro();
	void processTitle();

	void (CPassiveGalaxy::*processMode)();

	CBitmap m_BackgroundBitmap;
    CBitmap mCommanderTextSfc;
    CBitmap mKeenTextSfc;

    VectorD2<int> mCommanderTextPos;
    VectorD2<int> mKeenTextPos;

	bool m_restartVideo;

    int mTimer;

    int mtimeForTerminatorText;
};

}

#endif /* CPASSIVE_GALAXY_H_ */
