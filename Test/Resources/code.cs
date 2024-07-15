using System;

namespace Whale
{

    ///
    /// 程序类
    ///
    public class Program
    {

        ///
        /// 主函数
        /// param(args) 参数
        /// return() 程序返回值
        ///
        public static int Main(String[] args)
        {

            Console::Write("Hello, World!");
            Console::Pause();

            return 0;
        }

        ///
        ///
        ///
        public static T Lerp<T>(const T& x, const T& y, const T& t)
        {
            return x * (1 - t) + y * t;
        }

    }

}
