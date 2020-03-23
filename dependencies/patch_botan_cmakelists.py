
def should_discard_line(l):
	patterns = ['${PROJECT_NAME}_tests', '${PROJECT_NAME}_cli', '${PROJECT_NAME}_shared', 'CONFIGURATION_DUMMY']
	for p in patterns:
		if p in l:
			return True
	return False

f = open('botan/CMakeLists.txt', 'r')
content = f.read()
f.close()

f = open('botan/CMakeLists.txt', 'w')

for l in content.split('\n'):
	if not should_discard_line(l):
		f.write(l + '\n')

f.close()
