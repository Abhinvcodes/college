def reverse_file_content(input_file, output_file, mode='lines'):
    try:
        with open(input_file, 'r') as f:
            content = f.readlines()

        if mode == 'all':
            # Reverse every single character in the file
            reversed_content = "".join(content)[::-1]
        else:
            # Reverse the order of the lines (standard behavior)
            reversed_content = "".join(content[::-1])

        with open(output_file, 'w') as f:
            f.write(reversed_content)
            
        print(f"Success! Reverted content saved to {output_file}")

    except FileNotFoundError:
        print("Error: The source file does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

reverse_file_content('input.txt', 'output.txt', mode='all')
