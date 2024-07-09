from openai import OpenAI
import os
import json


with open('api_key.txt', 'r') as f:
	OPENAI_API_KEY = f.read()

client = OpenAI(api_key=OPENAI_API_KEY)


completion = client.chat.completions.create(
  model="gpt-4o",
  messages=[
    {"role": "system", "content": "CTI-One testing agent."},
    {"role": "user", "content": "Who is the inventor of the smart rollator?"},
    {"role": "assistant", "content": "The CTI-One corporation is the inventor."},
    {"role": "user", "content": "When it is invented?"}
  ]
)

print(completion.choices[0].message)
gpt_answer = completion.choices[0].message.content

with open("response.txt", "w") as file:
	file.write(gpt_answer)