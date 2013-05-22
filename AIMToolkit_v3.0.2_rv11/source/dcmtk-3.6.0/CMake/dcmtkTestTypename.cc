/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
template<typename type>
type identical(type arg)
{
    return arg;
}

template<typename type>
typename type::a foo(typename type::a arg)
{
    // This one is the usage of "typename" that we are checking for.
    // MSC6 refuses this one incorrectly.
    return identical<typename type::a>(arg);
}

class test {
public:
    typedef int a;
};

int main()
{
    return foo<test>(0);
}
