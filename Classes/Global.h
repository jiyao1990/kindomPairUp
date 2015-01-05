//
//  Global.h
//  kindomPairUp
//
//  Created by Jiyao on 14/11/3.
//
//

#ifndef __kindomPairUp__Global__
#define __kindomPairUp__Global__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define gGlobal      Global::getInstance()
#define gWinSize     Director::getInstance()->getWinSize()

#define TypeNum      5
#define TileHor      8         //横排个数
#define TileRow      8         //竖排个数


#define Zorder_Chose        100    //选中的zorder
#define Zorder_Mask         50     //遮罩的zorder
#define Zorder_Min          1      //最低的zorder

enum TypeLevel{
    
    TypeLevel_NULL = -1,
    TypeLevel_1 = 0,
    TypeLevel_2,
    TypeLevel_3,
    TypeLevel_4,
    TypeLevel_5,
    
    TypeLevel_len,
};

enum GameType{
    
    GameType_NULL  = -1,
    GameType_house = 0,
    GameType_clothes,
    GameType_grab,
    GameType_chef,
    GameType_traffic,
  
    GameType_len,
};


/**
 *  转化字符类函数
 */
template <class T>
std::string toString(T _T){
    std::stringstream _ss;
    _ss << _T;
    return _ss.str();
}

//生成随机数
template <class T>
T createRandomValue(T from, T to){
    
    if(to <= from) return to;
    
    int r = 0;
    
    //获取系统时间
    struct timeval now;
    gettimeofday(&now, NULL);
    
    //初始化随机种子
    //timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的
    unsigned rand_seed = (unsigned)(now.tv_sec*1000000 + now.tv_usec);    //都转化为毫秒
    srand(rand_seed);
    
    r = rand() % (to - from + 1) + from;
    return r;
}

template <class T>
T createRandomValueFloat(T from, T to)
{
    int rate = 10000;
    int fromInt = (int) (from * rate);
    int toInt = (int) (to * rate);
    
    int rand = createRandomValue(fromInt, toInt);
    
    return rand / (T) rate;
}

template <class T>
std::string createBuf(const char* _lhs,T _t)
{
    char bufTmp[1024];
    sprintf(bufTmp, _lhs,_t);
    return string(bufTmp);
}


class Global : public Node{
    

public:
    
    static Global* getInstance();
    
    void fitInScreen(Node* pNode);
    void fitOutScreen(Node* pNode);
    void fullScreen(Node* pNode);
    //子节点不出屏原比例拉伸
    void scaleFitInScreen_Child(Node* _node);
    
private:
    
    static Global* _instance;
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(Size, m_WinSize, WinSize);
    Size m_defaultWinSize;

    float getFitX();
    float getFitY();
};

#endif /* defined(__kindomPairUp__Global__) */
