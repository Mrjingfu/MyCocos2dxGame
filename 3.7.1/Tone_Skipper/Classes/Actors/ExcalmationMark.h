//
//  ExcalmationMark.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#ifndef __Tone_Skipper__ExcalmationMark__
#define __Tone_Skipper__ExcalmationMark__

#include "SceneItem.h"
class ExcalmationMark : public SceneItem
{
    friend class ActorFactory;
protected:
    ExcalmationMark();
    virtual ~ExcalmationMark();
public:
    virtual bool loadModel();
};

#endif /* defined(__Tone_Skipper__ExcalmationMark__) */
