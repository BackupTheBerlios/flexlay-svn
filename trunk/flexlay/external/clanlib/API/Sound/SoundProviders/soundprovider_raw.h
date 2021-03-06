/*
**  ClanLib SDK
**  Copyright (c) 1997-2005 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    (if your name is missing here, please add it)
*/

//! clanSound="Sound Providers"
//! header=sound.h

#ifndef header_sound_provider_raw
#define header_sound_provider_raw

#ifdef CL_API_DLL
#ifdef CL_SOUND_EXPORT
#define CL_API_SOUND __declspec(dllexport)
#else
#define CL_API_SOUND __declspec(dllimport)
#endif
#else
#define CL_API_SOUND
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#include "../soundprovider.h"

class CL_SoundProvider_Raw_Generic;

//: Sound provider in a raw PCM format (no header in file).
//- !group=Sound/Sound Providers!
//- !header=sound.h!
class CL_API_SOUND CL_SoundProvider_Raw : public CL_SoundProvider
{
//! Construction:
public:
	//: Constructs a sound provider based on some raw PCM data.
	//param sound_data: Raw PCM data.
	//param num_samples: Number of samples to be read out of sound_data.
	//param bytes_per_sample: The size of a sample in bytes. This is 2 for 16 bit, and 1 for 8 bit.
	//param stereo: True if sound is stereo (two channels).
	//param frequency: Playback frequency for sample data.
	CL_SoundProvider_Raw(
		void *sound_data,
		int num_samples,
		int bytes_per_sample,
		bool stereo,
		int frequency = 22050);

	virtual ~CL_SoundProvider_Raw();

//! Operations:
public:
	//: Called by CL_SoundBuffer when a new session starts.
	//return: The soundbuffer session to be attached to the newly started session.
	virtual CL_SoundProvider_Session *begin_session();

	//: Called by CL_SoundBuffer when a session has finished. After this call,
	//- <p>CL_SoundBuffer will not access the session anymore. It can safely be deleted
	//- here (and in most cases should be delete here).</p>
	virtual void end_session(CL_SoundProvider_Session *session);

//! Implementation:
private:
	CL_SoundProvider_Raw_Generic *impl;
};

#endif
