/*******************************************************************************
* 文 件 名: 模板方法模式.cpp
* 文件描述: 在需要定义固定流程但允许某些步骤可变的情况下非常有用，常见于框架设计中。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

// 抽象基类：定义算法的骨架
class Game {
public:
    // 模板方法：定义算法的固定流程
    void play() {
        initialize();
        startPlay();
        endPlay();
    }

    virtual ~Game() = default;

protected:
    // 步骤 1：初始化游戏 - 抽象方法，必须由子类实现
    virtual void initialize() = 0;

    // 步骤 2：开始游戏 - 抽象方法，必须由子类实现
    virtual void startPlay() = 0;

    // 步骤 3：结束游戏 - 钩子方法，可由子类选择性重写
    virtual void endPlay() {
        std::cout << "Game: Default endPlay implementation." << std::endl;
    }
};

// 具体子类：足球游戏
class Football : public Game {
protected:
    void initialize() override {
        std::cout << "Football Game: Initialized!" << std::endl;
    }

    void startPlay() override {
        std::cout << "Football Game: Started! Enjoy the game!" << std::endl;
    }

    void endPlay() override {
        std::cout << "Football Game: Finished! Thanks for playing!" << std::endl;
    }
};

// 具体子类：篮球游戏
class Basketball : public Game {
protected:
    void initialize() override {
        std::cout << "Basketball Game: Initialized!" << std::endl;
    }

    void startPlay() override {
        std::cout << "Basketball Game: Started! Enjoy the game!" << std::endl;
    }

    // 使用基类的默认 endPlay 实现
};

// 客户端代码
int main() {
    Game* footballGame = new Football();
    footballGame->play();
    std::cout << std::endl;

    Game* basketballGame = new Basketball();
    basketballGame->play();
    std::cout << std::endl;

    delete footballGame;
    delete basketballGame;

    return 0;
}