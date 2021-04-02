# SpellChecker

Программа по исправлению ввода.

Исправляет вводимые слова, если они не более чем на две правки отличаются от слов в словаре. Правкой может быть либо удаление одной буквы, либо добавление одной буквы, при условии что правки одного типа не могут идти сразу друг за другом.

Ввод тектса производится в формате:
[Слова словаря]
===
[Текст для исправления]
===

При исправлении текста:
Если слово находится в словаре, то оно выводится как есть.
Иначе, если у слова нет возможных вариантов исправления, то оно выводится как {[слово]?}
Если хотя бы один из вариантов требует одну правку, то игнорируются все варианты требующие две правки.
Если в результате всего остался более чем один вариант исправления, то выводятся все они в формате {[правка_1], [правка_2]}

В проекте имеются примеры работы и примеры тестов.