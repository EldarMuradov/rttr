/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014 Axel Menzel <info@axelmenzel.de>                             *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#ifndef __RTTR_INSTANCE_H__
#define __RTTR_INSTANCE_H__

#include "rttr/base/core_prerequisites.h"
#include "rttr/detail/misc_type_traits.h"

namespace rttr
{
class variant;
class type;

namespace detail
{
class argument;
/*!
 * This class is used for forwarding the instance of an object to the function calls.
 *
 * \remark You should never explicit instantiate this class by yourself.
 */
class RTTR_API instance
{
public:
    instance();

    instance(variant& var);

    instance(const instance& other);

    instance(instance&& other);

    template<typename T>
    instance(const T& data, typename std::enable_if<!std::is_same<instance, T>::value >::type* = 0);

    template<typename T>
    instance(T& data, typename std::enable_if<!std::is_same<instance, T>::value >::type* = 0);

    template<typename TargetType>
    TargetType* try_convert() const;

    bool is_valid() const;
    explicit operator bool() const;

    type get_type() const;

private:
    instance& operator=(const instance& other);

private:
    void*               m_data;
    const rttr::type    m_type;
};

} // end namespace detail
} // end namespace rttr

#include "rttr/detail/instance_impl.h"

namespace rttr
{

/*!
 * \brief Returns a dummy instance object.
 *         Use this function when you have a static \ref method or \ref property which you need to invoke.
 *
 * \return An instance object.
 */
RTTR_INLINE static detail::instance empty_instance() { return detail::instance(); }
} // end namespace rttr

#endif // __RTTR_INSTANCE_H__
