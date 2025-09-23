from abc import ABC, abstractmethod


class BaseTranslator(ABC):
    @abstractmethod
    def translate(self, text, target_lang) -> str:
        pass
