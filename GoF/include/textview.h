#ifndef _GOF_TEXTVIEW_H_
#define _GOF_TEXTVIEW_H_

#include <memory>
#include "gof_export.h"
#include "foundation.h"

namespace gof {

/** Adaptee becomes implementation detail in Adapter.
 * TextView holds a bouding box represented by bottom left corner, height
 * and width. Origin assumed at bottom left corner of screen.
 * @ingroup Adapter
 */
class GOF_EXPORT TextView
{
public:
    /// accepts four Coord values and define bounding box.
    TextView(Coord OriginX, Coord OriginY, Coord width, Coord height);
    /// destructor
    virtual ~TextView();
    /** Get Origin
     * @param x[out] horizontal distance of bottom-left corner from origin.
     * @param y[out] vertical  distance of bottom-left corner from origin.
     */
    void GetOrigin(Coord& x, Coord& y) const;
    /** Get Extent
     * @param width[out] horizontal distance of top-right corner from bottom-left.
     * @param height[out] vertical distance of top-right corner from bottom-left.
     */
    void GetExtent(Coord& width,Coord& height) const;
    /// checks if this object is empty.
    virtual bool IsEmpty() const;
private:
    struct pImpl;
    std::unique_ptr<pImpl> pimpl;
};

}

#endif
