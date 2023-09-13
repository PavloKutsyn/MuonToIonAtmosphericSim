// RNGWrapper.hh

template<class T>  // The class is a template, so it can work with any type T
class RNGWrapper {
  public:
    static void set(T* object, double (T::*func)(void));  // static function to set the RNG object and its method
    static double rng(void);  // static function to generate a random number using the RNG object
  private:
    static T* m_obj;  // Pointer to the RNG object
    static double (T::*m_func)(void);  // Pointer to member function of the RNG object which generates a random number
};

// The following are definitions for the static member variables
template<class T> T* RNGWrapper<T>::m_obj;  // Definition for m_obj
template<class T> double (T::*RNGWrapper<T>::m_func)(void);  // Definition for m_func

// Function to set the RNG object and its method.
// It takes a pointer to the RNG object and a pointer to the member function as parameters
template<class T> void RNGWrapper<T>::set(T* object, double (T::*func)(void)) {
  m_obj = object;
  m_func = func;
}

// Function to generate a random number
template<class T> double RNGWrapper<T>::rng(void) { return (m_obj->*m_func)(); }
