
#ifndef CyclicBufferH
#define CyclicBufferH

template <class T>
class TCyclicBuffer
{
	T * tBuffer_;
	int iSizeBuff_;       // размер циклического буфера
	int iPos_;            // позиция вставки и удаления (--iPos)


public:
	TCyclicBuffer(int size);
   ~TCyclicBuffer();

	void add(const T);        // поместить элемент сверху
	T pop();               // удалить   последний элемент

	T getElement(int item);   // получить  элемент

	bool resize(int newSize); // изменить размер буффера
	void clear();             // очистить все ячейки
	int size(){return iSizeBuff_;}

	bool isEmpty();
	bool isFull();

};
//----------------------------------------------------------------------------
template <class T>
TCyclicBuffer<T>::TCyclicBuffer(int size)
{
	iSizeBuff_ = size > 0 ? size: 10;   // инициализировать размер буфера
	tBuffer_ = new T[iSizeBuff_];       // выделить память под буфер
	iPos_ = 0;                          // значение 0 говорит о том, что стек пуст
}
//----------------------------------------------------------------------------
template <class T>
TCyclicBuffer<T>::~TCyclicBuffer()
{
	delete [] tBuffer_;
}
//----------------------------------------------------------------------------
template <class T>
void TCyclicBuffer<T>::add(const T item)
{
   if(iPos_ == iSizeBuff_) iPos_ = 0;
   tBuffer_[iPos_] = item;
   ++iPos_;
}
//----------------------------------------------------------------------------
template <class T>
T TCyclicBuffer<T>::pop()
{
   --iPos_;
   	T temp = tBuffer_[iPos_];
   if(iPos_ < 0)
   {
	 iPos_ = iSizeBuff_ - 1;
   }
   return temp;
}
//----------------------------------------------------------------------------
template <class T>
bool TCyclicBuffer<T>::isEmpty()
{
   if(iPos_ == 0) return true;
   else return false;
}
//----------------------------------------------------------------------------
template <class T>
bool TCyclicBuffer<T>::isFull()
{
   if(iPos_ == iSizeBuff_) return true;
   else return false;
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
