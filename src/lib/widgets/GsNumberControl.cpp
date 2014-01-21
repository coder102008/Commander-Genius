/*
 * CGUINumberControl.cpp
 *
 *  Created on: 06.03.2012
 *      Author: gerstrong
 */

#include <graphics/GsGraphics.h>
#include <base/CInput.h>
#include <base/video/CVideoDriver.h>
#include <lib/base/GsTimer.h>
#include <base/utils/StringUtils.h>

#include "GsNumberControl.h"


int CGUINumberControl::mTwirliconID = 10;

const int SLIDER_WIDTH = 16;



CGUINumberControl::CGUINumberControl(	const std::string& text,
					const int startValue,
					const int endValue,
					const int deltaValue,
					const int value,
					const bool slider ) :
mIncSel(false),
mDecSel(false),
mText(text),
mValue(value),
mStartValue(startValue),
mEndValue(endValue),
mDeltaValue(deltaValue),
mSlider(slider)
{
	mFontID = 1;
    
/*	if(g_pBehaviorEngine->getEngine() == ENGINE_VORTICON)
	{
	    drawButton = &CGUINumberControl::drawVorticonStyle;
	}
	else if(g_pBehaviorEngine->getEngine() == ENGINE_GALAXY)
	{

    }*/
	
	setupButtonSurface();
}


void CGUINumberControl::increment()
{
	setSelection(mValue+mDeltaValue);
}

void CGUINumberControl::decrement()
{
	setSelection(mValue-mDeltaValue);
}


bool CGUINumberControl::sendEvent(const InputCommands command)
{
	if(command == IC_STATUS || command == IC_JUMP || command == IC_RIGHT)
	{
		increment();
		return true;
	}
	else if(command == IC_LEFT)
	{
		decrement();
		return true;
	}
	return false;
}



const int CGUINumberControl::getSelection()
{
	return mValue;
}

void CGUINumberControl::setSelection( const int value )
{

	if( mStartValue>value )
		mValue = mStartValue;
	else if( mEndValue<value )
		mValue = mEndValue;
	else
		mValue = value;

	setupButtonSurface();
}


std::string CGUINumberControl::sliderStr()
{
	int ch;
	ch = (mDecSel) ? 8 : 1;
	std::string slider;
	slider = static_cast<char>(ch);

	const int sVal = (SLIDER_WIDTH-3)*(mValue - mStartValue) / (mEndValue - mStartValue);

	for( int l=0 ; l<sVal ; l++)
		slider += '\04';

	slider += '\05';

	for( int l=0 ; l<(SLIDER_WIDTH-3)-sVal ; l++)
		slider += '\06';

	ch = (mIncSel) ? 9 : 7;
	slider += static_cast<char>(ch);

	return slider;
}





void CGUINumberControl::processLogic()
{
	// Here we check if the mouse-cursor/Touch entry clicked on our Button
	if( PointingDevEvent *mouseevent = gInput.m_EventList.occurredEvent<PointingDevEvent>() )
	{
		CVec MousePos = mouseevent->Pos;

		if( mRect.HasPoint(MousePos) )
		{
            const float xMid = mRect.x+(mRect.w)/2.0f;

			if(mouseevent->Type == PDE_MOVED)
			{
				mDecSel = false;
				mIncSel = false;

                if( MousePos.x < xMid )
					mDecSel = true;
                else if( MousePos.x > xMid )
					mIncSel = true;

				mHovered = true;
				gInput.m_EventList.pop_Event();
			}
			else if(mouseevent->Type == PDE_BUTTONDOWN)
			{
				mPressed = true;
				gInput.m_EventList.pop_Event();
			}
			else if(mouseevent->Type == PDE_BUTTONUP)
			{
				mReleased = true;
				mHovered = true;
				mPressed = false;


                if( MousePos.x < xMid )
				{
					// Cycle through the values
					if( mValue > mStartValue )
						decrement();
				}
                else if( MousePos.x > xMid )
				{
					// Cycle through the values
					if( mValue < mEndValue )
						increment();
				}

				setupButtonSurface();
				gInput.m_EventList.pop_Event();
			}
		}
		else
		{
			mIncSel = false;
			mDecSel = false;
			mHovered = false;
			mPressed = false;
			mReleased = false;
		}
	}
}


void CGUINumberControl::drawVorticonStyle(SDL_Rect& lRect)
{

	SDL_Surface *blitsfc = gVideoDriver.getBlitSurface();

	// Now lets draw the text of the list control
	GsFont &Font = gGraphics.getFont(mFontID);

	Font.drawFont( blitsfc, mText, lRect.x+24, lRect.y, false );
	Font.drawFont( blitsfc, ":", lRect.x+24+mText.size()*8, lRect.y, false );

	if(mSlider)
	{
		gGraphics.getFont(2).drawFont( blitsfc, sliderStr(), lRect.x+16+(mText.size()+2)*8, lRect.y, false );
	}
	else
	{
		std::string text = (mDecSel) ? "\025" : " ";
		text += itoa(mValue);
		if(mIncSel)
			text += static_cast<char>(17);
		else
			text += " ";

		Font.drawFont( blitsfc, text, lRect.x+24+(mText.size()+2)*8, lRect.y, false );
	}

	drawTwirl(lRect);

}


void CGUINumberControl::processRender(const GsRect<float> &RectDispCoordFloat)
{

	// Transform to the display coordinates
	GsRect<float> displayRect = mRect;
	displayRect.transform(RectDispCoordFloat);
	SDL_Rect lRect = displayRect.SDLRect();

    SDL_Surface *blitsfc = gVideoDriver.getBlitSurface();

    if( mReleased )
    {
        drawRect( blitsfc, &lRect, 1, 0x00BBBBBB, 0x00CFCFCF );
    }
    else if( mPressed )
    {
        drawRect( blitsfc, &lRect, 1, 0x00BBBBBB, 0x00DFDFDF );
    }
    else if( mHovered )
    {
        drawRect( blitsfc, &lRect, 1, 0x00BBBBBB, 0x00EFEFEF );
    }
    else
    {
        drawRect( blitsfc, &lRect, 1, 0x00BBBBBB, 0x00FFFFFF );
    }

    // Now lets draw the text of the list control
    GsFont &Font = gGraphics.getFont(mFontID);

    Font.drawFontCentered( blitsfc, mText, lRect.x, lRect.w, lRect.y, lRect.h,false );


}
