//
//  QuestionMark.h
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#ifndef __Tone_Skipper__QuestionMark__
#define __Tone_Skipper__QuestionMark__

#include "UsableItem.h"
class QuestionMark : public UsableItem
{
    friend class ActorFactory;
public:
    typedef enum{
        QMT_HEART = 0,
        QMT_COLOR,
        QMT_RANDOM
    }
    QUESTION_MARK_TYPE;
protected:
    QuestionMark();
    virtual ~QuestionMark();
public:
    virtual bool loadModel();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    void setQuestionMarkType(QUESTION_MARK_TYPE type);
    
private:
    QUESTION_MARK_TYPE  m_QMType;
};

#endif /* defined(__Tone_Skipper__QuestionMark__) */
