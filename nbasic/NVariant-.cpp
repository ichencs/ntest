#include "NVariant.h"
#include <xtr1common>


// template <class T>
// inline void v_construct_helper(NVariant::Private* x, const T& t, std::false_type)
// {
// 	// 	x->data.shared = new QVariantPrivateSharedEx<T>(t);
// 	x->is_shared = true;
// }
//
// template <class T>
// inline void v_construct_helper(NVariant::Private* x, const T& t, std::true_type)
// {
// 	new (&x->data) T(t);
// 	x->is_shared = false;
// }





NVariant::NVariant()
{

}


NVariant::~NVariant()
{
}
