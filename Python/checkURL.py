def validate_url(url):
	"""Validates the given url passed as string.
	
	Arguments:
    url -- String, A valid url should be of form <Protocol>://<hostmain>/<fileinfo>
	
	Protocol = [http, https, ftp]
	Hostname = string
	Fileinfo = [.html, .csv, .docx]
	"""
	# your code starts here.
	Protocol = ["http", "https", "ftp"]

	Fileinfo = ["html", "csv", "docx"]
	splitP = url.split("://")
	if len(splitP)>=2 and splitP[0] in Protocol:
		splitFile = splitP[1].split("/")
		splitSy = splitP[1].split(".")
		if len(splitFile)>=2 and len(splitSy)>=2 and splitSy[-1] in Fileinfo:
			return True
	
	return False# return True if url is valid else False

def validate_url_regex(url):
	^\s*valid\_protocols.+(?=.*http)(?=.*https)(?=.*ftp).+


if __name__ == '__main__':
	# url = input("Enter an Url: ")
	url = "http://www.baidu.com/.html"
	print(validate_url(url))