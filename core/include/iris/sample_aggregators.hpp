#include <iris/sample_aggregators.h>


template
<
    typename Vector3Iterable, 
    typename Vector2Iterable
>
iris::Vector3 
iris::aggregate::uniform<Vector3Iterable, Vector2Iterable>
(
    Vector3Iterable colors, 
    Vector2Iterable /* samples */
)
{
    Vector3 sum(0);
    size_t n = 0;
    for (const Vector3& color : colors)
    {
        sum += color;
        ++n;
    }
            
    return sum / static_cast<float>(n);
}
