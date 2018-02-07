
#ifndef CyclicBufferH
#define CyclicBufferH

template <class T>
class TCyclicBuffer
{
	typedef int INDEX_T;     ////< псевдоним для индексов

	T * tBuffer_;            ////< указатель на буффер

	int iSizeBuff_;       	  ////< размер циклического буфера
	INDEX_T iPosRead_;        ////< позиция чтения
	INDEX_T iPosWrite_;       ////< позиция записи


public:
	TCyclicBuffer(int size);
   ~TCyclicBuffer();

	bool read(T& item);        		////< чтение из буффера
	bool write(const T& item);       ////< запись в буффер

	T getElement(INDEX_T item);   // получить  элемент

	bool resize(int newSize); // TODO: изменить размер буффера
	void clear();             // очистить все ячейки

	int size(){return iSizeBuff_;}
	int count(){return iPosWrite_ - iPosRead_;}

	bool isEmpty();
	bool isFull();

	inline T& operator[] (INDEX_T i)
	{
		if(IsEmpty() || i > Count())
			return T();
		return tBuffer_[iPosRead_++];
	}

	inline const T operator[] (INDEX_T i)const
	{
		if(IsEmpty())
			  return T();
		return tBuffer_[iPosRead_++];
	}

};
//----------------------------------------------------------------------------
template <class T>
TCyclicBuffer<T>::TCyclicBuffer(int size):iPosRead_(0), iPosWrite_(0)
{
	iSizeBuff_ = size > 0 ? size: 10;   // инициализировать размер буфера
	tBuffer_ = new T[iSizeBuff_];       // выделить память под буфер

}
//----------------------------------------------------------------------------
template <class T>
TCyclicBuffer<T>::~TCyclicBuffer()
{
	delete [] tBuffer_;
}
//----------------------------------------------------------------------------
template <class T>
bool TCyclicBuffer<T>::read(T& item)
{
   if(isEmpty()) return false;
   item = tBuffer_[iPosRead_];
   iPosRead_++;
   if(iPosRead_ + 1 > iSizeBuff_) iPosRead_= 0;
   return true;

}
//----------------------------------------------------------------------------
template <class T>
bool TCyclicBuffer<T>::write(const T& item)
{
   if(isFull()) return false;
   if(iPosWrite_ + 1 > iSizeBuff_)iPosWrite_ = 0;
   tBuffer_[iPosWrite_] = item;
   iPosWrite_++;
   return true;

}
//----------------------------------------------------------------------------
template <class T>
bool TCyclicBuffer<T>::isEmpty()
{
   return iPosRead_ == iPosWrite_;
}
//----------------------------------------------------------------------------
template <class T>
bool TCyclicBuffer<T>::isFull()
{
   return iPosWrite_ - iPosWrite_ == iSizeBuff_;
}
//----------------------------------------------------------------------------
template <class T>
T TCyclicBuffer<T>::getElement(int item)
{
   if(item >= 0 && item < iSizeBuff_) return tBuffer_[item];
   // если переполнение в плюс, то шагаем вперед по буферу
   else if(item > 0) return getElement(item - iSizeBuff_ - 1);
   // если переполнение в минус, то шагаем в обратную сторону с конца
   else return getElement(iSizeBuff_ + item);
}
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
