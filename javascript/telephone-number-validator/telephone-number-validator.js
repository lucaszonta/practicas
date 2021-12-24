function telephoneCheck(str) {
  let re = /^1?\s?(\(\d{3}\)|\d{3})(\s|-)?(\d{3}(\s|-)?\d{4})\b/;

  return (re.test(str)) ? true : false;
}

telephoneCheck("1(555)555-5555");