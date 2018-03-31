#include "vgamepadsimple.h"

#include <base/video/CVideoDriver.h>
#include <base/utils/FindFile.h>
#include <base/CInput.h>
#include <base/GsLogging.h>
#include <fileio/ResourceMgmt.h>


bool TouchButton::loadPicture(const std::string &picFile)
{
    const std::string buttonFname = getResourceFilename(picFile, "", true, true);
    if(buttonFname == "") return false;

    mTexture.load(GetFullFileName(buttonFname), gVideoDriver.Renderer());
    if( !mTexture )
    {
        gLogging.ftextOut("Failed to load the texture: %s!\n", picFile.c_str());
        return false;
    }

    mTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    return true;
}

VirtualKeenControl::~VirtualKeenControl()
{}

bool VirtualKeenControl::init()
{
#if SDL_VERSION_ATLEAST(2, 0, 0)
    GsWeakSurface blit(gVideoDriver.getBlitSurface());
    SDL_PixelFormat *format = blit.getSDLSurface()->format;

    const int buttonSize = 50;


    // Create the overlay surface and fill it with alpha 0
    mOverlay.create(0, blit.width(), blit.height(), 32, 0, 0, 0, 0);

    mOverlay.setBlendMode(SDL_BLENDMODE_BLEND);
    mOverlay.setAlpha(uint8_t(255.0f*mTranslucency));

    mOverlay.fill(SDL_MapRGBA(format, 0, 0, 0, 0 ));

    /// Draw a D-Pad

    // Left arrow
    const GsRect<Uint16> upRect(0, blit.height()-buttonSize, buttonSize, buttonSize);
    mOverlay.fill(upRect, SDL_MapRGBA(format, 128, 0, 0, 128 ));

    /// Load The buttons images
    {
        // Directional pad
        if(!mDPad.loadPicture("dpad.png")) return false;

        if(!mConfirmButton.loadPicture("confirm.png")) return false;

        if(!mStartButton.loadPicture("start.png")) return false;

        if(!mJumpButton.loadPicture("1.png")) return false;

        if(!mPogoButton.loadPicture("2.png")) return false;

        if(!mStatusButton.loadPicture("3.png")) return false;

        if(!mStatusButton.loadPicture("4.png")) return false;
    }

#endif

    return true;
}

        // Status Button
        if( !loadButtonTexture("4.png", mStatusButtonTexture) )
            return false;

bool VirtualKeenControl::ponder()
{
#if SDL_VERSION_ATLEAST(2, 0, 0)

    if(!mDPad.invisible)
    {
        const float dpadSize = 0.2f;

        const GsRect<float> dpadRect(0, 1.0f-dpadSize,
                                      dpadSize, dpadSize);

        mDPad.setRect(dpadRect);

        mDPad.mTexture.setAlpha(uint8_t(255.0f*mTranslucency));
    }

#endif

    return true;
}

void VirtualKeenControl::render(GsWeakSurface &sfc)
{
#if SDL_VERSION_ATLEAST(2, 0, 0)
    GsRect<Uint16> clickGameArea = gVideoDriver.mpVideoEngine->getActiveAreaRect();        

    auto addTexture = [](TouchButton &button) -> void
    {
        if(!button.invisible)
        {
            gVideoDriver.addTextureRefToRender(button.mTexture, button.Rect());
        }
    };

    addTexture(mDPad);

    /*
    addTexture(mStatusButton);

    if(mButtonMode == BUTTON_MODE::OK)
    {
        addTexture(mConfirmButton);
    }

    if(mButtonMode == BUTTON_MODE::WMAP &&
            !mHideStartButton)
    {
        addTexture(mStartButton);
        addTexture(mStatusButton);
    }*/

/*



    // On map, show the start button if keen approaches a level
    if(mButtonMode == BUTTON_MODE::WMAP && !mHideStartButton)
    {
        const float buttonSize = 0.1f;

        const Uint16 width = clickGameArea.w * buttonSize;
        const Uint16 height = clickGameArea.h * buttonSize;        

        const GsRect<Uint16> confirmRect(clickGameArea.w-2*width, clickGameArea.h-2*height, width, height);
        mStartButtonTexture.setAlpha(uint8_t(255.0f*mTranslucency));
        gVideoDriver.addTextureRefToRender(mStartButtonTexture, confirmRect);

        const GsRect<Uint16> statusButtonRect(clickGameArea.w*0.5f, clickGameArea.h-height, width, height);
        mStatusButtonTexture.setAlpha(uint8_t(255.0f*mTranslucency));
        gVideoDriver.addTextureRefToRender(mStatusButtonTexture, statusButtonRect);
    }

    if(mButtonMode == BUTTON_MODE::ACTION)
    {
        const float buttonSize = 0.1f;

        const Uint16 width = clickGameArea.w * buttonSize;
        const Uint16 height = clickGameArea.h * buttonSize;

        // Main controls
        const GsRect<Uint16> shootButtonRect(clickGameArea.w-2*width, clickGameArea.h-2*height, width, height);
        mShootButtonTexture.setAlpha(uint8_t(255.0f*mTranslucency));
        gVideoDriver.addTextureRefToRender(mShootButtonTexture, shootButtonRect);

        const GsRect<Uint16> jumpButtonRect(clickGameArea.w-2*width, clickGameArea.h-height, width, height);
        mJumpButtonTexture.setAlpha(uint8_t(255.0f*mTranslucency));
        gVideoDriver.addTextureRefToRender(mJumpButtonTexture, jumpButtonRect);

        const GsRect<Uint16> pogoButtonRect(clickGameArea.w-width, clickGameArea.h-height, width, height);
        mPogoButtonTexture.setAlpha(uint8_t(255.0f*mTranslucency));
        gVideoDriver.addTextureRefToRender(mPogoButtonTexture, pogoButtonRect);
    }*/
#endif
}


void VirtualKeenControl::mouseState(const Vector2D<float> &Pos, const bool down)
{
#if SDL_VERSION_ATLEAST(2, 0, 0)
    /// Menu Control process of one mouse state
    const float dpadSize = 0.2f;

    // Size of the buttons on the dpad
    const float dpadSizePiece = 0.3f*dpadSize;

    const float yBottom = 1.0f;
    const float yTop = yBottom-dpadSize;

    auto verifyButtonMatch = [&](const GsRect<float> &buttonRect,
                                 InputCommands cmd)
    {
        if( buttonRect.HasPoint(Pos) )
        {
            gInput.setCommand(0, cmd, down);
        }
    };


    if(Pos.y >= yTop && Pos.y < 1.0f)
    {
        SDL_Event ev;
        ev.type = (down ? SDL_KEYDOWN : SDL_KEYUP);

        if( !mDPad.invisible &&
             mDPad.isInside(Pos.x, Pos.y) )
        {
            // Y-Direction
            // Up presses
            if(Pos.y<yTop+dpadSizePiece)
            {
                ev.key.keysym.sym = SDLK_UP;
                SDL_PushEvent(&ev);
            }
            // Down presses
            else if(Pos.y>=yBottom-dpadSizePiece)
            {
                ev.key.keysym.sym = SDLK_DOWN;
                SDL_PushEvent(&ev);
            }

            // X-Direction
            // Left presses
            if(Pos.x<dpadSizePiece)
            {
                ev.key.keysym.sym = SDLK_LEFT;
                SDL_PushEvent(&ev);
            }
            // Right presses
            else if(Pos.x>=dpadSize-dpadSizePiece)
            {
                ev.key.keysym.sym = SDLK_RIGHT;
                SDL_PushEvent(&ev);
            }
        }

        /// Dpad presses
        if(Pos.x > dpadSize)
        {
            /// Then, if any other button was pressed...
            const float buttonSize = 0.1f;

            if(mButtonMode == BUTTON_MODE::OK)
            {
                // Was the Ok button pressed?
                GsRect<float> confirmRect(1.0f-2.0f*buttonSize,
                                          1.0f-2.0f*buttonSize,
                                          buttonSize, buttonSize);

                if( confirmRect.HasPoint(Pos) )
                {
                    ev.key.keysym.sym = SDLK_RETURN;
                    SDL_PushEvent(&ev);
                }
            }

            // On map if we can enter a level, let's enter!
            if(mButtonMode == BUTTON_MODE::WMAP && !mHideStartButton)
            {
                // Was the Ok button pressed?
                GsRect<float> confirmRect(1.0f-2.0f*buttonSize, 1.0f-2.0f*buttonSize, buttonSize, buttonSize);
                verifyButtonMatch(confirmRect, IC_JUMP);

                // Was the Status button pressed?
                const GsRect<float> statusButtonRect(0.5f, 1.0f-buttonSize, buttonSize, buttonSize);
                verifyButtonMatch(statusButtonRect, IC_STATUS);
            }


            if(mButtonMode == BUTTON_MODE::ACTION)
            {
                // Was the Shoot button pressed?
                const GsRect<float> shootButtonRect(1.0f-2.0f*buttonSize, 1.0f-2.0f*buttonSize, buttonSize, buttonSize);
                verifyButtonMatch(shootButtonRect, IC_FIRE);

                // Was the Jump button pressed?
                const GsRect<float> jumpButtonRect(1.0f-2.0f*buttonSize, 1.0f-buttonSize, buttonSize, buttonSize);
                verifyButtonMatch(jumpButtonRect, IC_JUMP);

                // Was the Pogo button pressed?
                const GsRect<float> pogoButtonRect(1.0f-buttonSize, 1.0f-buttonSize, buttonSize, buttonSize);
                verifyButtonMatch(pogoButtonRect, IC_POGO);
            }

            if(mShowStatusButton)
            {
                // Was the Status button pressed?
                const GsRect<float> statusButtonRect(0.5f, 1.0f-buttonSize, buttonSize, buttonSize);
                verifyButtonMatch(statusButtonRect, IC_STATUS);
            }
        }
    }
#endif

}
