import os
import firebase_admin
from firebase_admin import credentials, db
from dotenv import load_dotenv


# Load variables from .env
load_dotenv()


# Get Firebase URL
database_url = os.getenv("FIREBASE_DATABASE_URL")


# Firebase service account
cred = credentials.Certificate(
    "credentials/serviceAccountKey.json"
)


# Initialize Firebase
firebase_admin.initialize_app(
    cred,
    {
        "databaseURL": database_url
    }
)


print("Firebase connected successfully!")