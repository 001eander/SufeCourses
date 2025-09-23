from io import TextIOBase

from openai import OpenAI
from tomlkit import load

from trans.base import BaseTranslator
from trans.lang import Lang


class LLMTranslator(BaseTranslator):
    def __init__(self, model_name=None):
        try:
            with open("config/llm.toml", encoding="utf-8") as f:
                config = load(f)["translate"]

            self._model_name = (
                model_name if model_name else config["default_model"]
            )

            self._client = OpenAI(
                api_key=config["api_key"],
                base_url=config["base_url"],
            )
        except Exception as e:
            raise RuntimeError(f"Failed to initialize LLM client: {e}")

    def translate(self, text, target_lang=Lang.ENGLISH):
        if isinstance(text, list):
            text = "\n".join(text)
        elif isinstance(text, TextIOBase):
            text = text.read().encode("utf-8")

        _map = {
            Lang.ENGLISH: "英语",
            Lang.CHINESE: "汉语",
            Lang.FRENCH: "法语",
            Lang.GERMAN: "德语",
            Lang.WYW: "文言文",
        }

        try:
            with open("config/llm.toml", encoding="utf-8") as f:
                config = load(f)["translate"]

            message = {
                "role": "user",
                "content": config["prompt"].format(
                    text=text,
                    target_lang=_map[target_lang],
                ),
            }

            completion = self._client.chat.completions.create(
                model=self._model_name, messages=[message]
            )

            translated_text = completion.choices[0].message.content

            return translated_text
        except Exception as e:
            print(f"Error during translation: {e}")
            return text
