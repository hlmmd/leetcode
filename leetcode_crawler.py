import requests
import bs4
import json
import re
import time

root_url = 'https://leetcode.com'
contest_info_api = 'https://leetcode.com/contest/api/info/weekly-contest-'
question_urls = 'https://leetcode.com/graphql'


# 获取contest对应的discuss id
# 返回的是一个json，直接用json解析


def get_discuss_id(contest_num):
    url = contest_info_api + str(contest_num)
    req = requests.get(url=url)
    html = req.text
    try:
        json_result = json.loads(html)
        return json_result['contest']['discuss_topic_id']
    except:
        print('json decode error')
        return -1


def get_content(discuss_topic_id):

    # 生成post的content参数
    req_json = {
        "operationName": "DiscussTopic",
        "variables": {
            "topicId": 1163970
        },
        "query": "query DiscussTopic($topicId: Int!){topic(id:$topicId){post{content}}}"
    }
    req_json["variables"]["topicId"] = discuss_topic_id

    headers = {'Content-Type': 'application/json;charset=UTF-8'}
    res = requests.request("post", question_urls,
                           json=req_json, headers=headers, timeout=60)
    return res.text


def get_problems_detail(question_url):
    if question_url[-1] == '/':
        question_url = question_url[:-1]
    question_str = question_url.split('/')[-1]
    req_json = {"operationName": "questionData", "variables": {"titleSlug": "check-if-the-sentence-is-pangram"},
                "query": "query questionData($titleSlug: String!) {\n  question(titleSlug: $titleSlug) {\n    questionId\n    questionFrontendId\n    boundTopicId\n    title\n    titleSlug\n    content\n    translatedTitle\n    translatedContent\n    isPaidOnly\n    difficulty\n    likes\n    dislikes\n    isLiked\n    similarQuestions\n    exampleTestcases\n    contributors {\n      username\n      profileUrl\n      avatarUrl\n      __typename\n    }\n    topicTags {\n      name\n      slug\n      translatedName\n      __typename\n    }\n    companyTagStats\n    codeSnippets {\n      lang\n      langSlug\n      code\n      __typename\n    }\n    stats\n    hints\n    solution {\n      id\n      canSeeDetail\n      paidOnly\n      hasVideoSolution\n      paidOnlyVideo\n      __typename\n    }\n    status\n    sampleTestCase\n    metaData\n    judgerAvailable\n    judgeType\n    mysqlSchemas\n    enableRunCode\n    enableTestMode\n    enableDebugger\n    envInfo\n    libraryUrl\n    adminUrl\n    __typename\n  }\n}\n"}

    req_json['variables']['titleSlug'] = question_str
    headers = {'Content-Type': 'application/json;charset=UTF-8'}
    res = requests.request("post", question_urls,
                           json=req_json, headers=headers, timeout=60)

    res_json = json.loads(res.text)
    return res_json


def get_markdown(response):
    res_json = json.loads(response)
    content = res_json["data"]["topic"]["post"]["content"]
    lines = content.split('\n')
    question_urls = []
    for line in lines:
        # 找到所有()中的字符串，进行过滤
        reg = re.compile('\((.*?)\)')
        urls = re.findall(reg, line)
        for url in urls:
            if url.startswith('/problems/'):
                question_urls.append(root_url+url)

    markdown_strs = []
    for url in question_urls:
        res_json = get_problems_detail(url)
        questionFrontendId = res_json["data"]["question"]["questionFrontendId"]
        title = res_json["data"]["question"]["title"]
        content = res_json["data"]["question"]["content"]
        difficulty = res_json["data"]["question"]["difficulty"]
        onestr = "### [{} {}. {}]({})\n".format(
            questionFrontendId, difficulty, title, url)
        print(onestr)

        markdown_strs.append(onestr)

    return markdown_strs


if __name__ == '__main__':
    contest_num = 237
    print('## Weekly Contest {}\n'.format(contest_num))
    print(time.strftime("%Y.%m.%d", time.localtime()) + "\n")

    discuss_topic_id = get_discuss_id(contest_num)
    response = get_content(discuss_topic_id)
    markdown_strs = get_markdown(response)
