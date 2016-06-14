#ifndef IRIS_MATH_H
#define IRIS_MATH_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Math utility methods.
 */


namespace iris
{
    namespace constant
    {
        constexpr float m_pi = 3.1415926535897932384f;
        constexpr float m_2_pi = 2.0f * m_pi;
    }

    /**
     * Solves the quadratic equation ax^2 + bx + c = 0
     */
    bool solve_quadratic
    (
        float a, float b, float c,
        float& x0, float& x1
    );

    /**
     * Computes the average value of a collection.
     */
    template <typename Value, typename Iterator>
    Value average(Iterator begin, Iterator end)
    {
        Value sum = Value(0);
        size_t n = 0;
        for (Iterator it = begin; it != end; ++it)
        {
            sum += *it;
            ++n;
        }
            
        return sum / static_cast<float>(n);
    };
    /**
     * Computes the weighted average value of a collection.
     */
    template
    <
        typename Value, 
        typename ValueIterator,
        typename WeightIterator
    >
    Value weighted_average
    (
        ValueIterator value_begin, 
        ValueIterator value_end,
        WeightIterator weight_begin)
    {
        Value sum_values = Value(0);
        float sum_weights = 0.0f;

        WeightIterator weight_it = weight_begin;
        for (ValueIterator value_it = value_begin; 
             value_it != value_end; 
             ++value_it, ++weight_it)
        {
            sum_values += *weight_it * *value_it;
            sum_weights += *weight_it;
        }
            
        return sum_values / sum_weights;
    };

    /**
     * Evaluates 2D gaussian.
     */
    float gaussian_2d
    (
        float x, float y,
        float x0, float y0,
        float sigma_x, float sigma_y,
        float A
    );
    /**
     * Evalutes 2D isotrpic gaussian.
     */
    float gaussian_2d_isotropic
    (
        float x, float y,
        float x0, float y0,
        float sigma
    );
}


#endif  // IRIS_MATH_H
