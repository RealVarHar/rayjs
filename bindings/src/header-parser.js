export class HeaderParser {
    parseEnums(input) {
        const matches = [...input.matchAll(/((?:\/\/.+\n)*)typedef enum {\n([^}]+)} ([^;]+)/gm)];
        return matches.map(groups => {
            return {
                description: this.parseComments(groups[1]),
                values: this.parseEnumValues(groups[2]),
                name: groups[3],
            };
        });
    }
    parseEnumValues(input) {
        let lastNumber = 0;
        return input.split('\n')
            .map(line => line.trim().match(/([^ ,]+)(?: = ([0-9]+))?,?(?: *)(?:\/\/ (.+))?/))
            .filter(x => x !== null && !x[0].startsWith("/"))
            .map(groups => {
                let val = lastNumber = groups[2] ? parseInt(groups[2]) : lastNumber;
                lastNumber++;
                return {
                    name: groups[1],
                    description: groups[3] || "",
                    value: val
                };
            });
    }
    parseComments(input) {
        return input.split('\n').map(x => x.replace("// ", "")).join('\n').trim();
    }
    parseFunctionDefinitions(input) {
        const matches = [...input.matchAll(/^[A-Z]+ (.+?)(\w+)\(([^\)]+)\);(?: +\/\/ (.+))?$/gm)];
        return matches.map(groups => ({
            returnType: groups[1].trim(),
            name: groups[2],
            params: this.parseFunctionArgs(groups[3]),
            description: groups[4] || "",
            binding:{}
        }));
    }
    parseFunctions(input, noPrefix = false) {
        const matches = noPrefix
            ? [...input.matchAll(/((?:\/\/.+\n)+)^(.+?)(\w+)\(([^\)]+)\)/gm)]
            : [...input.matchAll(/((?:\/\/.+\n)+)^[A-Z]+ (.+?)(\w+)\(([^\)]+)\)/gm)];
        return matches.map(groups => ({
            returnType: groups[2].trim(),
            name: groups[3],
            params: this.parseFunctionArgs(groups[4]),
            description: groups[1] ? this.parseComments(groups[1]) : "",
            binding:{}
        }));
    }
    parseFunctionArgs(input) {
        return input.split(',').filter(x => x !== 'void').map(arg => {
            arg = arg.replaceAll("*", " * ").replaceAll('[',' [ ').replace(new RegExp("\\s+",'g'),' ').trim();
            const frags = arg.split(' ');
            const name = frags.pop();
            const type = frags.join(' ');
            return { name: name || "", type: type.trim(), binding:{} };
        });
    }
    parseStructs(input) {
        return [...input.matchAll(/((?:\/\/.+\n)+)typedef struct {([^}]+)} ([^;]+);/gm)].map(groups => ({
            name: groups[3],
            fields: this.parseStructFields(groups[2]),
            description: this.parseComments(groups[1])
        }));
    }
    parseStructFields(input) {
        return input.trim().split("\n").map(x => x.trim()).filter(x => !x.startsWith("/") && x.endsWith(";")).map(x => {
            const match = x.match(/([^ ]+(?: \*)?) ([^;]+);/);
            return {
                name: match[2],
                type: match[1],
                description: ""
            };
        });
    }
}