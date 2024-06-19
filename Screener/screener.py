import hashlib
import os
import json
import asyncio
from pyppeteer import launch
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor

# Path to temp directory to save PNG generated
temp_dir = "./temp/"
os.makedirs(temp_dir, exist_ok=True)

# Load domains
try:
    with open('domains.json', 'r') as f:
        domains = json.load(f)
except (FileNotFoundError, json.JSONDecodeError) as e:
    print(f"Error loading domains.json: {e}")
    domains = []

# Check if history.json exists, otherwise create an empty history
history_file = 'history.json'
if not os.path.exists(history_file):
    history = []
    with open(history_file, 'w') as f:
        json.dump(history, f)
else:
    try:
        with open(history_file, 'r') as f:
            history = json.load(f)
    except (FileNotFoundError, json.JSONDecodeError) as e:
        print(f"Error loading history.json: {e}")
        history = []

def file_hash(file_path):
    """Compute SHA-1 hash of a file."""
    sha1 = hashlib.sha1()
    with open(file_path, 'rb') as f:
        while chunk := f.read(8192):
            sha1.update(chunk)
    return sha1.hexdigest()

def array_to_json(hash_array, file_path):
    """Write an array to a JSON file."""
    with open(file_path, 'w', encoding='utf8') as f:
        json.dump(hash_array, f, ensure_ascii=False, indent=4)
    print("HISTORY UPDATED")

def read_history():
    """Read history file and convert it to JSON array."""
    return [{'domain': entry['domain'], 'hash': entry['hash']} for entry in history]

def domain_updated_or_not(history_array, new_hash):
    """Check if hash is in the history array."""
    if any(item['hash'] == new_hash for item in history_array):
        return "/notUpdated/"
    else:
        return "/updated/"

def move_to_another_folder(src, dst):
    """Move file from src to dst, ensuring dst does not already exist."""
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    if os.path.exists(dst):
        os.remove(dst)
    os.rename(src, dst)

async def take_screenshot(page, domain, filename, protocol='https'):
    """Take a screenshot of the given domain."""
    try:
        await page.goto(f"{protocol}://{domain}", {'waitUntil': 'load', 'timeout': 30000})
        await asyncio.sleep(5)  # Wait for 5 seconds
        await page.screenshot({'path': filename})
        return True
    except Exception as e:
        print(f"Error for {protocol}://{domain} > {e}")
        return False

async def process_domains(domains, base_dir):
    browser = await launch(
        headless=True,
        ignoreHTTPSErrors=True,
        args=['--ignore-certificate-errors', '--no-sandbox'],
        executablePath='C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe'  # Change this path to your Chrome/Chromium installation
    )
    page = await browser.newPage()
    await page.setViewport({'width': 1920, 'height': 1080, 'deviceScaleFactor': 1})

    # Add event listener for dialog (SSL error dialogs)
    page.on('dialog', lambda dialog: asyncio.ensure_future(dialog.accept()))

    hash_png = []

    dt = datetime.now()
    finale_date = dt.strftime("%d-%m-%Y-%H-%M-%S")

    for index, entry in enumerate(domains):
        domain = entry.get('domain')
        if not domain:
            print(f"Skipping invalid entry: {entry}")
            continue
        filename = os.path.join(temp_dir, f"{domain}.png")
        print(f"[{index + 1}] Running screenshot for {domain}")

        success = await take_screenshot(page, domain, filename)
        if not success:
            # Retry with www
            domain_with_www = f"www.{domain}"
            filename_with_www = os.path.join(temp_dir, f"{domain_with_www}.png")
            print(f"Retrying with {domain_with_www}")
            success = await take_screenshot(page, domain_with_www, filename_with_www)
            if success:
                filename = filename_with_www
        
        if not success:
            # Retry with HTTP
            print(f"Retrying with HTTP for {domain}")
            success = await take_screenshot(page, domain, filename, protocol='http')
            if not success:
                domain_with_www = f"www.{domain}"
                filename_with_www = os.path.join(temp_dir, f"{domain_with_www}.png")
                print(f"Retrying with HTTP for {domain_with_www}")
                success = await take_screenshot(page, domain_with_www, filename_with_www, protocol='http')
                if success:
                    filename = filename_with_www

        if success:
            current_hash = await asyncio.get_running_loop().run_in_executor(None, file_hash, filename)
            print(f"Checking history for {filename}")

            if len(history) == 0:
                dir_history = "/notUpdated/"
            else:
                current_history = await asyncio.get_running_loop().run_in_executor(None, read_history)
                dir_history = await asyncio.get_running_loop().run_in_executor(None, domain_updated_or_not, current_history, current_hash)

            new_directory_name = os.path.join(base_dir, finale_date + dir_history)
            new_file_name = os.path.join(new_directory_name, os.path.basename(filename))
            await asyncio.get_running_loop().run_in_executor(None, move_to_another_folder, filename, new_file_name)
            print(f"Saved in {new_file_name}")
            hash_png.append({'domain': domain, 'hash': current_hash})
        else:
            hash_png.append({'domain': domain, 'hash': 'ERROR'})

    await browser.close()
    await asyncio.get_running_loop().run_in_executor(None, array_to_json, hash_png, history_file)
    print("DONE")

async def main():
    await process_domains(domains, "res/domains")

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except Exception as e:
        print(f"Error running main: {e}")

