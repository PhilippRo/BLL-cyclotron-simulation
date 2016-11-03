/*
 * Channel.h
 *
 *  Created on: 16.07.2016
 *      Author: philipp
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

// # in a macro is a stringyfication
#define SET_UP_CHANNEL_NAME(a) a.name=#a;

#include <list>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace BLL {

template<class T>
class Channel {
private:
	std::list<T> qu;
	boost::mutex writemutex;
	int capaticity = 10000;
public:
	std::string name = "";
	Channel() {
		// TODO Auto-generated constructor stub

	}

	~Channel() {
		// TODO Auto-generated destructor stub
	}

	//implement templated functions in headers comp problems
	T read(){
		bool empty = true;
		do{
			writemutex.lock();
			empty = qu.size() == 0;
			writemutex.unlock();
		}while(empty);
		writemutex.lock();
		T ret;
		ret = qu.front();
		qu.pop_front();
		writemutex.unlock();
		return ret;
	}

	void write(T content){
		bool full = true;
		do{
			writemutex.lock();
			full = qu.size() > capaticity;
			writemutex.unlock();
		}while(full);
		writemutex.lock();
		qu.push_back(content);
		writemutex.unlock();
	}

};

} /* namespace BLL */

#endif /* CHANNEL_H_ */
