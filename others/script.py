import subprocess
import sys
import os

def clone_and_build(ssh_url):
    # Extract the repository path from the SSH URL
    repo_path = ssh_url.split(':', 1)[1]

    # Extract the username and repository name from the repository path
    user_name, _ = repo_path.split('/', 1)

    # Create the directory with the user's name
    os.makedirs(user_name, exist_ok=True)

    # Clone the repository into the user's directory
    subprocess.run(['git', 'clone', ssh_url, user_name], check=True)

    # Change to the new directory
    os.chdir(user_name)

    print("PATH from script:", os.environ['PATH'])

    # Run the 'pipex' binary (or whatever command you need)
    subprocess.run(['/Users/stefano/francinette/tester.sh'], check=True)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py git@github.com:username/repo.git")
        sys.exit(1)

    ssh_url = sys.argv[1]
    clone_and_build(ssh_url)

