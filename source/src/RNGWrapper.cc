/*In essence, the RNGWrapper class acts as an interface to
 * any type of random number generator, allowing the underlying
 *  generator and its random number generation method
 *  to be easily swapped out as needed without requiring
 *  changes to the code that uses this random number generation.*/

#include "RNGWrapper.hh"
#include "Randomize.hh"

template CLHEP::HepRandomEngine* RNGWrapper<CLHEP::HepRandomEngine>::m_obj;

template double (CLHEP::HepRandomEngine::*RNGWrapper<CLHEP::HepRandomEngine>::m_func)(void);

