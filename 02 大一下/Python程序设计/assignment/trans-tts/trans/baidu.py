import random
from hashlib import md5
from io import TextIOBase

import requests
from tomlkit import load

from trans.base import BaseTranslator
from trans.lang import Lang


class BaiduTranslator(BaseTranslator):
    def __init__(self):
        try:
            with open("config/baidu.toml") as f:
                config = load(f)["tranlate"]
            self.appid = config["appid"]
            self.appkey = config["appkey"]
            self.url = config["url"]
        except Exception as e:
            print(f"Error loading Baidu config: {e}")
            raise RuntimeError("Baidu translator config not found or invalid")

    def __make_md5(self, s):
        return md5(s.encode("utf-8")).hexdigest()

    def __get_salt_and_sign(self, text):
        salt = random.randint(32768, 65536)
        sign = self.__make_md5(self.appid + text + str(salt) + self.appkey)
        return salt, sign

    def translate(self, text, target_lang=Lang.ENGLISH):
        if isinstance(text, list):
            text = ". ".join(text)
        elif isinstance(text, TextIOBase):
            text = text.read().encode("utf-8")

        salt, sign = self.__get_salt_and_sign(text)

        params = {
            "appid": self.__appid,
            "q": text,
            "from": "auto",
            "to": target_lang,
            "salt": salt,
            "sign": sign,
        }

        try:
            r = requests.post(
                self.__url,
                params=params,
                headers={"Content-Type": "application/x-www-form-urlencoded"},
            )
            return r.json()["trans_result"][0]["dst"]
        except Exception as e:
            print(f"Error in Baidu translation: {e}")
            return text
