#pragma once


template<typename T>
class ArrayBase abstract : public ListStore<T, POD<T>::Result>, public virtual IEnumerable<T>
{

};

template<typename T, typename K = typename KeyType<T>::Type>
class ListBase abstract : public ArrayBase<T>
{

};