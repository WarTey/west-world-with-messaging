#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
	Msg_HiEveryone,
	Msg_SilenceYoungMadman,
	Msg_CalmDown,
	Msg_HorribleHeadache,
	Msg_DontComeToSaloon,
	Msg_GetDownToBusiness,
	Msg_GoSleep
};


inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case 0:
		return "HiHoneyImHome";

	case 1:
		return "StewReady";

	case 2:
		return "Hi everyone!";

	case 3:
		return "Silence young madman, I have a huge headache!";

	case 4:
		return "Calm down sir, I was just saying hello! If it's a problem for you just stand up and come with me outside.";

	case 5:
		return "Okay, let's go outside! But I can't and don't want to calm down! My head hurts too much!";

	case 6:
		return "If you have such a headache, don't come to a saloon where everyone is talking loudly!";

	case 7:
		return "Okay, I can see that the soft way doesn't work with you so let's get down to business!";

	case 8:
		return "You should better go home to sleep!";

	default:
		return "Not recognized!";
	}
}

#endif
