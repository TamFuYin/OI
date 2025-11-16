import tkinter as tk
from tkinter import scrolledtext as st
import openai
openai.api_key="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"
def translate(text,lang="zh-CN"):
    prompt=f"把下面的文本翻译成{lang}:\n\n{text}"
    response=openai.chat.completions.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role":"system","content":"你是一个翻译助手，保证翻译准确且流畅，行内公式用 \\(\\) 包裹，行间公式用 \\[\\] 包裹"},
            {"role":"user","content": prompt}
        ],
        max_tokens=200
    )
    return response.choices[0].messages['content']
root=tk.Tk()
root.title("AI翻译器")
tk.Label(root,text="请输入要翻译的文本:").pack()
input_text=st.ScrolledText(root,width=80,height=10)
input_text.pack()
tk.Label(root,text="目标语言:").pack()
lang_var=tk.StringVar(value="zh-CN")
tk.OptionMenu(root,lang_var,"zh-CN","en-US","ja-JP").pack()
tk.Button(root,text="翻译",command=lambda:input_text.insert("insert",translate(input_text.get("1.0","end-1c"),lang_var.get()))).pack()
root.mainloop()