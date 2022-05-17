import re
text = '''/*this is a
multiline comment*/'''

comment = re.compile(r'/\*(?:.|\n)*?\*/')
print(comment.findall(text))