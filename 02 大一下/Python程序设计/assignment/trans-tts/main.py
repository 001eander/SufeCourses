from trans.llm import LLMTranslator
from trans.lang import Lang

text = "La lueur du soleil couchant qui frappait en plein son visage pâlissait le lasting de sa soutane, luisante sous les coudes, effiloquée par le bas."
translator = LLMTranslator()
translated_text = translator.translate(text, target_lang=Lang.CHINESE)
print(translated_text)
