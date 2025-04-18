from PIL import Image
import csv

# Define image dimensions
width = 1920
height = 1080

def create_image_from_csv(csv_file):
    # Open the CSV file
    with open(csv_file, newline='') as file:
        reader = csv.reader(file)
        pixels = list(reader)

    # Ensure the number of pixels matches the expected resolution
    if len(pixels) != width * height:
        print(f"Error: The CSV file does not contain the expected {width * height} pixels.")
        return

    # Create a new image with RGB mode
    img = Image.new("RGB", (width, height))

    # Iterate over the pixels and set each one
    for i, row in enumerate(pixels):
        if len(row) != 3:
            print(f"Error: Each row in the CSV file should contain exactly 3 values (R, G, B).")
            return

        # Parse the RGB values
        try:
            r, g, b = map(int, row)
        except ValueError:
            print(f"Error: Invalid RGB values at row {i + 1}.")
            return

        # Calculate the x, y position on the image
        x = i % width
        y = i // width

        # Set the pixel color
        img.putpixel((x, y), (r, g, b))

    # Save the image to a file
    img.save("output_image.png")
    print("Image created successfully and saved as 'output_image.png'.")

# Call the function with the path to your CSV file
csv_file = "output"  # Replace with your CSV file path
create_image_from_csv(csv_file)
