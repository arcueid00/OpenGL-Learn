//
//  StringSupport.hpp
//  MyGLGame
//
//  Created by Katsuhiko Tamura on 2018/09/22.
//  Copyright © 2018年 Katsuhiko Tamura. All rights reserved.
//

#ifndef StringSupport_hpp
#define StringSupport_hpp

#include <string>
#include <stdexcept>

/*! printf()関数の書式でC++文字列を作成します（1023文字以内）。 */
std::string FormatString(const char* format, ...);

/*! 指定された名前のファイルに対応したパス文字列を取得します。 */
std::string GetFilepath(const std::string& filename);

/*! 指定された名前のテキストファイルを文字列として読み込みます。 */
std::string ReadTextFile(const std::string& filename);

/*! ゲーム実行中に起きるエラーを表す例外クラス */
class GameError : public std::runtime_error
{
public:
    template<typename... T>
    GameError(const char *format, T... args)
    : std::runtime_error(FormatString(format, args...)) {}
    
    GameError(const std::string& message)
    : std::runtime_error(message) {}
    
};

#endif /* StringSupport_hpp */
