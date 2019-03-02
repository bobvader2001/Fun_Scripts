import re
import requests


def get_vrm():
    vrm_in = input("Please enter a vehicle number plate: ")
    vrm = vrm_in.replace(" ", "")
    return vrm


def req_info(vrm):
    cookies = {"hpi.vrm": vrm}
    data = {"vrm": vrm}

    print(f"\nRequesting vehicle information for {vrm}...")
    r = requests.get("https://www.instantcarcheck.co.uk/product-selection", data=data, cookies=cookies)
    print("Done!")
    return r.text


def parse_info(html):
    output_info = {}
    
    vehicle_info = re.findall(r'<div class=\"col-sm-9.*<form', html)[0]
    parsed_info = re.findall(r'<div class=\"col-xs-2.+?>(.+?)<\/div><div class=.+?>([^<]+)', vehicle_info)

    for pair in parsed_info:
        key = pair[0].lower()
        value = pair[1]
        output_info[key] = value

    return output_info


def format_info(parsed_info):
    formatted_info = ""
    
    for key, value in parsed_info.items():
        if key == "bhp":
            key = key.upper()
        else:
            key = key.title()

        if key != "Reg":
            value = value.title()

        formatted_info += key + ": " + value + "\n"

    return formatted_info


def main():
    vrm = get_vrm()
    info_page = req_info(vrm)
    parsed_info = parse_info(info_page)
    formatted_info = format_info(parsed_info)

    print("\n" + formatted_info)


if __name__ == "__main__":
    main()
