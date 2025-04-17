import cv2
import numpy as np
from tkinter import Tk
from tkinter.filedialog import askopenfilename, asksaveasfilename
import time
from collections import deque

def flood_fill(binary_image, seed_x, seed_y):
    h, w = binary_image.shape
    mask = np.zeros((h, w), dtype=np.uint8)
    stack = [(seed_x, seed_y)]
    while stack:
        x, y = stack.pop()
        if mask[x, y] or not binary_image[x, y]:
            continue
        x_left, x_right = x, x
        while x_left > 0 and binary_image[x_left - 1, y]:
            x_left -= 1
        while x_right < h - 1 and binary_image[x_right + 1, y]:
            x_right += 1
        mask[x_left:x_right + 1, y] = 1
        for nx in range(x_left, x_right + 1):
            if y > 0 and binary_image[nx, y - 1] and not mask[nx, y - 1]:
                stack.append((nx, y - 1))
            if y < w - 1 and binary_image[nx, y + 1] and not mask[nx, y + 1]:
                stack.append((nx, y + 1))
    return mask
    
def find_contours(binary_image):
    contours, _ = cv2.findContours(binary_image.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return contours

def calculate_line_metrics(line, image_height, image_width):
    (x1, y1), (x2, y2) = line
    if (y1 == image_height - 1 and y2 == image_height - 1):
        return None
    if (0 <= x1 <= 2 and y1 == image_height - 1) or (0 <= x2 <= 2 and y2 == image_height - 1):
        return None
    if (image_width - 3 <= x1 < image_width and y1 == image_height - 1) or (image_width - 3 <= x2 < image_width and y2 == image_height - 1):
        return None
    length = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    slope = (y2 - y1) / (x2 - x1) if x2 != x1 else None
    return length, slope

def approximate_lines_from_contours(contours, image_height, image_width):
    lines = []
    for contour in contours:
        perimeter = cv2.arcLength(contour, True)
        epsilon = 0.005 * perimeter
        approx = cv2.approxPolyDP(contour, epsilon, True)
        if len(approx) >= 2:
            for i in range(len(approx)):
                start_point = tuple(approx[i][0])
                end_point = tuple(approx[(i + 1) % len(approx)][0])
                line_metrics = calculate_line_metrics((start_point, end_point), image_height, image_width)
                if line_metrics:  
                    lines.append((start_point, end_point, line_metrics))
    return lines

def main():
    Tk().withdraw() # Get image from file explorer
    open_path = askopenfilename(title='Select an image')
    if not open_path:
        print("No file selected. Exiting.")
        return
    image = cv2.imread(open_path)
    if image is None:
        print("Failed to read image. Exiting.")
        return
    
    start_time = time.time()
    
    h, w = image.shape[:2]

    rgb_threshold = 66 # Convert image to binary using RGB threshold
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, binary_image = cv2.threshold(gray_image, rgb_threshold, 1, cv2.THRESH_BINARY)


    seed_x, seed_y = h - 1, w // 2 # Perform flood-fill from bottom-center
    filled_mask = flood_fill(binary_image, seed_x, seed_y)

    contours = find_contours(filled_mask) # Find the contours of the filled region

    lines = approximate_lines_from_contours(contours, h, w) # Approximate the contours into line segments

    for i, (start_point, end_point, (length, slope)) in enumerate(lines):
        if length < 2:
            continue
        print(f"Line {i + 1}:")
        print(f"  Start Point: {start_point}")
        print(f"  End Point: {end_point}")
        print(f"  Length: {length:.2f}")
        print(f"  Slope: {'Vertical line' if slope is None else f'{slope:.2f}'}")
            
    print(time.time()-start_time) # Track time for optimisation
    
    save_path = asksaveasfilename(title="Save the line-segment image", defaultextension=".png", filetypes=[("PNG files", "*.png"), ("All Files", "*.*")])
    if save_path: # Save the result with the lines drawn on the image
        output = np.zeros((h, w, 3), dtype=np.uint8)  # Blank RGB image
        output[filled_mask == 1] = [255, 255, 255]  # Color the filled region in white
        for line in lines: # Draw the lines on the output image
            start_point, end_point, _ = line
            cv2.line(output, start_point, end_point, (0, 0, 255), 2)
        cv2.imwrite(save_path, output)
        print(f"Saved line-segment image to {save_path}")
    else:
        print("Not saved.")
        
if __name__ == "__main__":
    main()



