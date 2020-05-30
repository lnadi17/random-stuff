import requests
import time

headers = {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:74.0) Gecko/20100101 Firefox/74.0'}

login_url = 'https://archive.org/account/login'
loan_url = 'https://archive.org/services/loans/beta/loan/'

pics_path = 'psixo/'

with requests.Session() as s:
    payload = {'username': 'goderdza1315225@gmail.com', 'password': '????????'}

    r = s.get(login_url)
    cookies = dict(r.cookies)

    r = s.post(login_url,
            data=payload,
            headers=headers,
            cookies=cookies)

    r = s.post(loan_url,
            data={'action': 'create_token', 'identifier': 'psychoanalysisli00crew'})

    with open('list.txt', 'r') as f:
        counter = 0
        skip_until = 282
        was_error = False

        while True:
            if not was_error:
                url = f.readline()

            if url == '':
                break

            if counter < skip_until:
                print("Skipping " + str(counter) +'.jpg')
                counter += 1
                continue
            
            print('Downloading ' + str(counter) + '.jpg')

            with open(pics_path + str(counter) + '.jpg', 'wb') as handle:
                try:
                    response = s.get(url, stream=True)

                    if not response.ok:
                        print(response)

                    for block in response.iter_content(1024):
                        if not block:
                            break

                        handle.write(block)

                    was_error = False
                    time.sleep(1)
                except:
                    print('Remote closed, trying again ;)')
                    time.sleep(3)
                    was_error = True
                    counter -= 1

            counter += 1
        
        print("Done.")
