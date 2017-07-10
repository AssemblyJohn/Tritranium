#ifndef __TRITRANIUM_RENDERABLE__
#define __TRITRANIUM_RENDERABLE__

#include "Platform\Platform.h"

#include "Property.h"


BEGIN_TRITRANIUM

class YRenderable : public YProperty
{
	YOBJECT_VARS(YRenderable);
};

YOBJECT_FUNCTIONS(YRenderable, YProperty);

END_TRITRANIUM

#endif