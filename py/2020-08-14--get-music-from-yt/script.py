import os
import time
import pafy
import yaml
from pydub import AudioSegment
import eyed3
from datetime import datetime
import string
import random

try:
    if not os.path.exists('downed'):
        os.mkdir("downed")
    if not os.path.exists('final'):
        os.mkdir("final")

    with open("config.yaml", 'r') as stream:
        config = yaml.safe_load(stream)

    print("loaded these urls:")
    for vid in config["Vids"]:
        print("---" + vid["Url"])

    print("\nnow getting audio from the urls...")
    for vid in config["Vids"]:
        pafyvid = pafy.new(vid["Url"])
        print("---title: " + pafyvid.title)

        print("   audiostreams:")
        for a in reversed(pafyvid.audiostreams):
            print("      ", a.bitrate, a.extension, a.get_filesize())

        bestaudio = pafyvid.getbestaudio()
        print("   best bitrate: " + bestaudio.bitrate)

        # rawfilename = "downed/"+pafyvid.title+"."+bestaudio.extension
        rawfilename = "downed/" + ''.join(random.choices("1680qscrgvhu", k=24))
        mp3filename = "final/"+vid["Title"]+".mp3"
        print("   raw filename: " + rawfilename)
        print("   target filename: " + mp3filename)

        bestaudio.download(rawfilename)
        print("   downloaded")

        audioseg = AudioSegment.from_file(rawfilename)
        audioseg.export(mp3filename, format="mp3")
        print("   exported")

        audiofile = eyed3.load(mp3filename)
        audiofile.tag.title = vid["Title"]
        audiofile.tag.artist = vid["Artist"]
        audiofile.tag.album = vid["Album"]
        audiofile.tag.album_artist = vid["Artist"]
        audiofile.tag.year = vid["Year"]
        audiofile.tag.track_num = vid["TrackNum"]
        audiofile.tag.save()
        print("   tags changed and done")

        time.sleep(config["SleepSeconds"])

except yaml.YAMLError as exc:
    print(exc)
except OSError as exc:
    print(exc)
except IOError as exc:
    print(exc)

print("finished")
