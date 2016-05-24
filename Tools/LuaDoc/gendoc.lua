require "markdown"

input = io.open(arg[1],"r")
if input == nil then
	return 0
end

inputFileName = arg[1]
outputFileName = inputFileName..".md"
path = arg[2] or ""

--output = io.open(outputFileName,"w")

text = input:read("*all")
outbuffer = ""
prototypes = {}

for doc in string.gmatch(text, "/%*%*lua.-%*/") do
	tagList = {}
	tagList.param = {}
	tagList.desc = {}
	tagList.returns = {}
	tagList.example = {}
	-- Extract usefull info
	-- Extract function prototype
	_,_, prototype = doc:find("/%*%*lua (.-)%c")
	-- Add emphasis on types :
	prototype = prototype:gsub(":(%a+)",":%*%1%*")
	prototype = prototype:gsub("(.-)%(","%*%*%1%*%*%(")
	table.insert(prototypes,prototype)
	-- Extract tags
	for tag in string.gmatch(doc,"@%a+[^@%*]*") do
		-- remove control characters
		tag = tag:gsub("%c*$","")

		_, _, tagType, tagContent = tag:find("@(%a+)(.*)")
		
		if tagType == "param" then
			_,_,tagParam,tagContent = tagContent:find("(%S+) (.*)")
			_,n,parameter,_type = tagParam:find("([%a_]*):?(%a*)")
			if _type and _type ~="" then
				t = "**"..parameter.."**:*".._type.."*"
			else
				t = "**"..parameter.."**"
			end
			
			table.insert(tagList[tagType],t.." " ..tagContent)
		elseif tagType == "desc" then
			
			table.insert(tagList.desc,tagContent)
		elseif tagType == "return" then
			
			table.insert(tagList.returns,tagContent)
		elseif tagType == "example" then
			_, _, title, content = tagContent:find("([^\n]*)\n*(.-)!eend")
			title = title:gsub("%c*$","")
			content = content:gsub("%c*$","")
			print("example :"..content.."\n")
			--content = content:gsub("\n","\n\n")
			table.insert(tagList.example,"##### " ..title .."\n\n<pre>\n"..content.."\n</pre>")
		end


	end
	outbuffer = outbuffer .. "\n- - -\n### <a name=\""..#prototypes.."\"></a>" .. prototype

	if #tagList.desc > 0 then
		outbuffer = outbuffer .. "\n\n#### Description\n"
		for _,v in ipairs (tagList.desc) do
			outbuffer = outbuffer .."\n".. v 
		end
	end

	if #tagList.param > 0 then
		outbuffer = outbuffer .. "\n\n#### Parameters"
		for _,v in ipairs (tagList.param) do
			outbuffer = outbuffer .."\n- ".. v 
		end
	end

	if #tagList.returns > 0 then
		outbuffer = outbuffer .. "\n\n#### Return"
		for _,v in ipairs (tagList.returns) do
			outbuffer = outbuffer .."\n- ".. v 
		end
	end

	if #tagList.example > 0 then
		outbuffer = outbuffer .. "\n\n#### Example"
		for _,v in ipairs (tagList.example) do
			outbuffer = outbuffer .."\n".. v 
		end
	end
end

-- write the summary

mdBuffer = ""
mdBuffer = mdBuffer .. "# ArenIA Lua API\n\n"

mdBuffer = mdBuffer .. "## Table of Contents\n\n"
for k,v in ipairs(prototypes) do
	mdBuffer = mdBuffer .. "- ["..v.."](#"..k..")\n"
end

mdBuffer = mdBuffer .. "- - -\n\n"
mdBuffer = mdBuffer .. outbuffer

-- OMG WHY DID I DID THIS ?
--os.execute("perl "..path.."Markdown.pl "..outputFileName.." > "..inputFileName..".tmp")



--mdResult = io.open(inputFileName..".tmp")
--mdResultText = mdResult:read("*all")

mdResultText = markdown(mdBuffer);
mdResultText = mdResultText:gsub("<pre>","<pre><code class=\"lua\">")
mdResultText = mdResultText:gsub("</pre>","</code></pre>")

template = io.open(path.."template.html")
templateText = template:read("*all")
template:close()

finalOutput = io.open(inputFileName..".html","w")
--text = templateText:gsub("%<%!%-%-replacetitle%>%<%!%-%-%>",inputFileName)
text = templateText:gsub("%<%!%-%-replaceme%>%<%!%-%-%>",mdResultText)
finalOutput:write(text)
finalOutput:close()