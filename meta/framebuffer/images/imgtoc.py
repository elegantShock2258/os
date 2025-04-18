import argparse
from PIL import Image
import numpy as np

def image_to_c_array(image_path, output_file, var_name="image_data"):
    image = Image.open(image_path).convert("RGB")
    width, height = image.size
    pixels = np.array(image)
    
    with open(output_file, "w") as f:
        f.write("#ifndef IMAGE_DATA_H\n#define IMAGE_DATA_H\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write(f"#define IMAGE_WIDTH {width}\n")
        f.write(f"#define IMAGE_HEIGHT {height}\n\n")
        f.write(f"static const uint8_t {var_name}[{height}][{width}][3] = {{\n")
        
        for y in range(height):
            f.write("    { ")
            for x in range(width):
                r, g, b = pixels[y, x]
                f.write(f"{{ {r}, {g}, {b} }}, ")
            f.write("},\n")
        
        f.write("};\n\n#endif // IMAGE_DATA_H\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert an image to a C array.")
    parser.add_argument("input", help="Path to input image file")
    parser.add_argument("output", help="Path to output C header file")
    args = parser.parse_args()
    
    image_to_c_array(args.input, args.output)
