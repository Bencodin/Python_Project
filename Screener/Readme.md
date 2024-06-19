# Website Screenshot Taker

This Python script takes screenshots of a list of websites and saves them in organized directories. The script also maintains a history of taken screenshots to determine if a website has been updated.

## Requirements

- Python 3.7+
- Google Chrome or Chromium installed
- `pyppeteer` library
- `hashlib`, `os`, `json`, `asyncio`, `datetime`, `concurrent.futures` (standard Python libraries)

## Setup

1. **Install the required Python libraries:**

    ```bash
    pip install pyppeteer
    ```

2. **Install Google Chrome or Chromium:**
   Ensure you have Google Chrome or Chromium installed on your system. Update the `executablePath` in the script if necessary to point to the correct installation path.

3. **Prepare the `domains.json` file:**

    Create a `domains.json` file in the same directory as the script. This file should contain a list of domains you want to take screenshots of. Example:

    ```json
    [
        {"domain": "google.com"},
        {"domain": "example.com"}
    ]
    ```

4. **Ensure the `history.json` file exists:**

    If the `history.json` file doesn't exist, the script will create an empty one. Make sure it's correctly formatted if it exists:

    ```json
    []
    ```

## Usage

1. **Run the script:**

    ```bash
    python screener.py
    ```

2. **Adding More Domains:**

    To add more domains to be processed, simply update the `domains.json` file with the new domains in the format mentioned above.

## Script Explanation

The script performs the following steps:

1. **Load the list of domains** from the `domains.json` file.
2. **Load or create a history file** (`history.json`) to keep track of previously processed screenshots.
3. **Compute SHA-1 hashes** for the screenshots to detect changes.
4. **Take screenshots** of the domains using `pyppeteer`.
5. **Retry with different protocols (https, http)** and subdomains (www) if the initial attempt fails.
6. **Compare the hashes** of new screenshots with the history to determine if a site has been updated.
7. **Save screenshots in organized directories** based on whether they have been updated or not.
8. **Update the history file** with the new screenshots' hashes.

## Handling Errors

If there are errors such as missing `domains.json` or `history.json` files, or issues with taking screenshots, the script will print appropriate error messages and continue processing the next domain.

## Note

- Ensure the `domains.json` file is correctly formatted and includes valid domain entries.
- Make sure the `history.json` file is properly initialized as an empty array `[]` if starting fresh.

## Example Output

The screenshots will be saved in the `res/domains` directory with subdirectories indicating whether the site was updated or not based on the hash comparison.
