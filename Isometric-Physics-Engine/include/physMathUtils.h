//math utilities

//square root finder - Heron's method
float sqrt_approx(float number) {
    if (number <= 0) return 0;

    float x = number;
    float y = 1.0f;
    const float epsilon = 0.00001f;  // precision

    while (x - y > epsilon) {
        x = (x + y) * 0.5f;
        y = number / x;
    }
    return x;
}
