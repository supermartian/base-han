# base-han

A naive encoding method inspired by base64, which encodes bytes to UTF-8 Chinese characters.

# Encoding/Decoding examples

	==Testing UTF-8 encoding/decoding ===
	这是一个测试项，用来测试utf8
	跨桦螎蜫亸犀磣汪热仨掯喦覚紻二拧梢柞螩亵皋撿啙枝丸
	这是一个测试项，用来测试utf8

	==Testing ASCII encoding/decoding ===
	lel
	獬侱一一一
	lel

	==Testing Long ASCII encoding/decoding ===
	llellellellellellellellellellellellellellellellellellelel
	穬羕擆椙乬穥掱哆杛乬獬羱呖椛乥穬羕擆椙乬穥掱哆杛乬獬羱呖椛乥穬羕擆椙乥乬一一一一
	llellellellellellellellellellellellellellellellellellelel

	==Testing binary encoding/decoding ===
	2 3 4 5 6 7 
	儂成繠丁一
	2 3 4 5 6 7 
	=====

	==Testing long binary encoding/decoding ===
	2 3 4 5 6 7 3 4 5 6 7 3 4 5 6 7 
	儂成繠仁丄吅娜幀侁万
	2 3 4 5 6 7 3 4 5 6 7 3 4 5 6 7 
	=====
