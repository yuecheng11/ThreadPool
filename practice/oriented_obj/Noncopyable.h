 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 10:59:02
 ///
 
#ifndef _MY_NONCOPYABLE_H_
#define _MY_NONCOPYABLE_H_

namespace wd
{

class Noncopyable
{
protected:
	Noncopyable(){}

private:
	Noncopyable(const Noncopyable & rhs);
	Noncopyable & operator=(const Noncopyable & rhs);
};
}

#endif
